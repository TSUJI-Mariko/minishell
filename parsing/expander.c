/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:31:35 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/14 11:31:40 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void check_path(t_minishell *ms, t_node *node) {
    char *str = node->cmds->str;
    if (ft_strchr(str, '/')) {
        node->is_exist = check_x(str);
        node->pathname = ft_strdup(str);
        return ;
    }
    str = ft_strjoin("/", str);
    char **paths = get_paths(ms);
    
    int i = 0;
    while (paths[i]) {
        char *pathname = ft_strjoin(paths[i++], str);
        if (check_x(pathname)) {
            node->pathname = pathname;
            node->is_exist = true;
            break;
        }
        free(pathname);
    }
    free(paths);
}

void filename_generation(t_minishell *ms, t_node *node) {
    if (node == NULL)
        return;
    if (node->kind == ND_PIPE) {
        filename_generation(ms, node->lhs);
        filename_generation(ms, node->rhs);
    }
    if (node->kind == ND_CMD) {
        // cmds
        if (check_builtin(node->cmds->str))
            node->is_builtin = true;
        else
            check_path(ms, node);
    }
}

char *var_expansion_str(t_minishell *ms, char *str) {
    char *ret = ft_calloc(1, sizeof(char));
    
    long i = 0;
    while (str[i] != '\0') {
        // $$
        if (str[i] == '$' && str[i + 1] == '$') {
            ret = ft_strjoin_with_free(ret, true, "$$", false);
            i += 2;
            continue;
        }

        // $\0
        if (str[i] == '$' && str[i + 1] == '\0') {
            ret = ft_strjoin_with_free(ret, true, "$", false);
            break;
        }

        // $var
        if (str[i] == '$') {
            i++;
            long j = 0;
            while (str[i + j] != '$' && str[i + j] != '\'' && str[i + j] != '"' && str[i + j] != '\0')
                j++;
            char *var_name = ft_strndup(&(str[i]), j);
            t_env *env = find_env(ms, var_name);
            free(var_name);
            if (env)
                ret = ft_strjoin_with_free(ret, true, env->body, false);
            i += j;
            continue;
        }

        long j = 0;
        while (str[i + j] != '\0' && str[i + j] != '$') {
            if (str[i + j] == '\'') {
                j++;
                while (str[i + j] != '\'')
                    j++;
            }
            j++;
        }
        char *tmp = ft_strndup(&(str[i]), j); 
        ret = ft_strjoin_with_free(ret, true, tmp, true);
        i += j;
    }
    free(str);
    return ret;
}

char *rm_quote(char *str) {
    while (ft_strchr(str, '\'')) {
        char *p = ft_strchr(str, '\'');
        char *before = ft_strndup(str, p - str);
        char *after = ft_strdup(p + 1);
        free(str);
        str = ft_strjoin_with_free(before, true, after, true);
    }
    while (ft_strchr(str, '"')) {
        char *p = ft_strchr(str, '"');
        char *before = ft_strndup(str, p - str);
        char *after = ft_strdup(p + 1);
        free(str);
        str = ft_strjoin_with_free(before, true, after, true);
    }   
    return str;
}

void var_expansion(t_minishell *ms, t_node *node) {
    if (node == NULL)
        return;
    
    if (node->kind == ND_PIPE) {
        var_expansion(ms, node->lhs);
        var_expansion(ms, node->rhs);
    }
    
    if (node->kind == ND_CMD) {
        t_node *cmd = node->cmds;
        t_node *redir_in = node->redir_in;
        t_node *redir_out = node->redir_out;
        while (cmd) {
            var_expansion(ms, cmd);
            cmd = cmd->next;
        }
        while (redir_in) {
            var_expansion(ms, redir_in);
            redir_in = redir_in->next;
        }
        while (redir_out) {
            redir_out = redir_out->next;
        }
    }

    if (node->kind == ND_WORD) {
        node->str = var_expansion_str(ms, node->str);
        node->str = rm_quote(node->str);
    }
}

void expander(t_minishell *ms, t_node *node) {
    var_expansion(ms, node);
    filename_generation(ms, node);
}

